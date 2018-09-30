package com.fthdgn.app.util;

import javafx.fxml.FXMLLoader;

import java.io.IOException;

public class FXMLUtil {
    public static <T> T load(String xml) {
        try {
            return FXMLLoader.load(FXMLUtil.class.getResource("/" + xml));
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }
}
