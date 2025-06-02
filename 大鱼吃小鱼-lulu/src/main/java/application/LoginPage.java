package application;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;


public class LoginPage extends Application {


    @Override
    public void start(Stage primaryStage) throws Exception {
        try {
            Parent root = FXMLLoader.load(LoginPage.class.getResource("/application/LoginScene1.fxml"));
            //load scene
            Scene scene = new Scene(root, 1000, 700);
            scene.getStylesheets().add(LoginPage.class.getResource("/application/styling.css").toExternalForm());
            //for decorating the gui
            primaryStage.setScene(scene);
            primaryStage.setX(0);
            primaryStage.setY(0);
            primaryStage.setTitle("Fish Eat Fish Game");

            Image icon = new Image(LoginPage.class.getResourceAsStream("/application/outfit4.png"));
            primaryStage.getIcons().add(icon);

            primaryStage.show();
            primaryStage.setResizable(false);

            primaryStage.setOnShown(event -> {
                root.requestFocus();
            });

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
