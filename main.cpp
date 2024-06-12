import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QPushButton, QMessageBox,
                             QVBoxLayout, QLineEdit, QLabel, QComboBox, QCheckBox,
                             QSlider, QHBoxLayout)
from PyQt5.QtCore import Qt

class EnhancedApp(QWidget):
    def __init__(self):
        super().__init__()

        # Initialize the user interface
        self.initUI()

    def initUI(self):
        # Set the main window properties
        self.setWindowTitle('Enhanced Qt Application')
        self.setGeometry(100, 100, 400, 300)

        # Create the main vertical layout
        main_layout = QVBoxLayout()

        # Create a horizontal layout for input elements
        input_layout = QHBoxLayout()

        # Create a QLineEdit widget for text input
        self.text_input = QLineEdit(self)
        self.text_input.setPlaceholderText('Enter some text')
        input_layout.addWidget(self.text_input)

        # Create a QComboBox widget for selecting options
        self.combo_box = QComboBox(self)
        self.combo_box.addItems(['Option 1', 'Option 2', 'Option 3'])
        input_layout.addWidget(self.combo_box)

        # Add the input layout to the main layout
        main_layout.addLayout(input_layout)

        # Create a QCheckBox widget
        self.checkbox = QCheckBox('Check me', self)
        main_layout.addWidget(self.checkbox)

        # Create a QSlider widget for selecting a value
        self.slider = QSlider(Qt.Horizontal, self)
        self.slider.setRange(0, 100)
        self.slider.setValue(50)
        self.slider.valueChanged.connect(self.updateSliderLabel)  # Connect the slider value change to a method
        main_layout.addWidget(self.slider)

        # Create a QLabel widget to display the slider value
        self.slider_label = QLabel(f'Slider Value: {self.slider.value()}', self)
        main_layout.addWidget(self.slider_label)

        # Create a QPushButton widget
        self.button = QPushButton('Show Message', self)
        self.button.clicked.connect(self.showMessage)  # Connect the button click to a method
        main_layout.addWidget(self.button)

        # Create a QLabel widget to display the result
        self.result_label = QLabel('Result will be displayed here', self)
        main_layout.addWidget(self.result_label)

        # Set the main layout for the window
        self.setLayout(main_layout)

    def showMessage(self):
        """
        Method to display a message box with the current state of the input widgets
        and update the result label with the same information.
        """
        text = self.text_input.text()  # Get the text from the QLineEdit
        combo_text = self.combo_box.currentText()  # Get the current text from the QComboBox
        checkbox_state = 'Checked' if self.checkbox.isChecked() else 'Unchecked'  # Check if the QCheckBox is checked
        slider_value = self.slider.value()  # Get the current value of the QSlider

        # Create a message string with the current input values
        message = (f'Input Text: {text}\n'
                   f'Selected Option: {combo_text}\n'
                   f'Checkbox is {checkbox_state}\n'
                   f'Slider Value: {slider_value}')
        
        # Display the message box
        QMessageBox.information(self, 'Message', message)

        # Update the result label with the current input values
        self.result_label.setText(f'Text: {text}, Option: {combo_text}, Checkbox: {checkbox_state}, Slider: {slider_value}')

    def updateSliderLabel(self, value):
        """
        Method to update the slider label with the current slider value.
        """
        self.slider_label.setText(f'Slider Value: {value}')

def main():
    """
    The main function to create and display the application window.
    """
    app = QApplication(sys.argv)  # Create the application object
    ex = EnhancedApp()  # Create an instance of the EnhancedApp class
    ex.show()  # Show the application window
    sys.exit(app.exec_())  # Start the event loop

if __name__ == '__main__':
    main()
