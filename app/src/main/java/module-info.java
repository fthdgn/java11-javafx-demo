module template {
    requires javafx.controls;
    requires javafx.fxml;
    opens template to javafx.graphics;
    opens template.controller to javafx.fxml;
}