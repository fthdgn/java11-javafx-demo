package template.controller;

import template.util.StringUtil;
import javafx.event.ActionEvent;
import javafx.scene.control.TextField;

public class MainController {
    public TextField outputTextField;
    public TextField inputTextField;

    public void reverseButtonClicked(ActionEvent actionEvent) {
        outputTextField.setText(StringUtil.reverse(inputTextField.getText()));
    }

}
