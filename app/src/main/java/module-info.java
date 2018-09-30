module com.fthdgn.app {
    requires javafx.controls;
    requires javafx.fxml;
    opens com.fthdgn.app to javafx.graphics;
    opens com.fthdgn.app.controller to javafx.fxml;
}