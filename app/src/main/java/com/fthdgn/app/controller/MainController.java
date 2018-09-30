package com.fthdgn.app.controller;

import com.fthdgn.app.util.StringUtil;
import javafx.event.ActionEvent;
import javafx.scene.control.TextField;

public class MainController {
    public TextField outputTextField;
    public TextField inputTextField;

    public void reveseButtonClicked(ActionEvent actionEvent) {
        outputTextField.setText(StringUtil.reverse(inputTextField.getText()));
    }

}
