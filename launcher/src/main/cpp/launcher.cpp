#if defined(__APPLE__) || defined(__linux__)
#include <cstdlib>
#include <dlfcn.h>
#elif _WIN32
#include <windows.h>
#endif
#include <jni.h>


const int Message(char *z)
{
#if defined(__APPLE__) || defined(__linux__)
    printf("%s\n", z);
#elif _WIN32
    MessageBox(0, (LPCSTR)z, (LPCSTR) "Error", MB_SETFOREGROUND);
#endif
    return 1;
}

#if defined(__APPLE__) || defined(__linux__)
int main(int argc, char **argv)
#elif _WIN32
int wmain(int argc, wchar_t *argv[])
#endif
{
    JavaVMOption options[2];
    options[0].optionString = "--module-path=.";
    options[1].optionString = _MODULE_NAME;

    JavaVMInitArgs vm_args;
    vm_args.version = JNI_VERSION_10;
    vm_args.nOptions = 2;
    vm_args.ignoreUnrecognized = JNI_FALSE;
    vm_args.options = options;

#if defined(__APPLE__) || defined(_WIN32)
#ifdef _WIN32
    HINSTANCE jvm_dll = LoadLibrary(TEXT("bin\\server\\jvm.dll"));
#elif __APPLE__
    void* jvm_dll = dlopen("./lib/server/libjvm.dylib", RTLD_LOCAL);
#endif
    if (jvm_dll == NULL)
    {
        Message("Cannot load jvm library.");
        exit(1);
    }
    typedef jint(JNICALL *JNI_CreateJavaVM_ptr)(JavaVM **, void **, void *);
#ifdef _WIN32
    JNI_CreateJavaVM_ptr createJavaVM_ptr = (JNI_CreateJavaVM_ptr)GetProcAddress(jvm_dll, "JNI_CreateJavaVM");
#elif __APPLE__
    JNI_CreateJavaVM_ptr createJavaVM_ptr = (JNI_CreateJavaVM_ptr)dlsym(jvm_dll, "JNI_CreateJavaVM");
#endif
    if (createJavaVM_ptr == NULL)
    {
        Message("Cannot load JNI_CreateJavaVM function");
        exit(1);
    }
#endif
#endif

    JavaVM *jvm;
    JNIEnv *env;
#ifdef __linux__
    jint res = JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
#else
    jint res = createJavaVM_ptr(&jvm, (void **)&env, &vm_args);
#endif
    if (res < 0)
    {
        Message("Cannot start JVM");
        exit(1);
    }

    jclass mainClass = env->FindClass(_MAIN_CLASS_NAME);
    if (!mainClass)
    {
        Message("Cannot find class");
        exit(1);
    }

    jmethodID mainMethod = env->GetStaticMethodID(mainClass, "main", "([Ljava/lang/String;)V");
    if (!mainMethod)
    {
        Message("Cannot find main method");
        exit(1);
    }

    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray args = env->NewObjectArray(argc - 1, stringClass, 0);
    for (int i = 1; i <= argc; i++)
    {
        jstring str = env->NewStringUTF((char *)argv[i]);
        env->SetObjectArrayElement(args, i - 1, str);
    }
    env->CallStaticVoidMethod(mainClass, mainMethod, args);
    jvm->DestroyJavaVM();
}
