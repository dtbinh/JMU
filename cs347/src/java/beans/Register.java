package beans;

import com.opensymphony.xwork2.ActionSupport;
import static org.apache.commons.lang3.text.WordUtils.capitalizeFully;

public class Register extends ActionSupport {

    String inputUserReg, inputEmail, inputFirstName, inputLastName, inputFullName, inputPasswordReg, inputPasswordConf, radio, classes;

    RegisterDao rdao = new RegisterDao();

    @Override
    public String execute() throws ClassNotFoundException {
        if (rdao.checkUser(inputUserReg)) {
            addActionError("This username has already been taken. Please choose another.");
            return INPUT;
        }

        if (rdao.checkEmail(inputEmail)) {
            addActionError("This email has already been taken. Please choose another.");
            return INPUT;
        }

        inputFullName = capitalizeFully(inputFirstName.trim()) + " " + capitalizeFully(inputLastName.trim());

        rdao.insertData(inputUserReg, inputPasswordReg, inputFullName, radio, inputEmail, classes);
        
        addActionMessage("Congratulations! You have successfully registered! Please login with your username and password.");
        return SUCCESS;
    }

    @Override
    public void validate() {
        if ("".equals(inputUserReg)) {
            addActionError("Username cannot be empty.");
        }
        if ("".equals(inputEmail)) {
            addActionError("Password cannot be empty.");
        }
        if ("".equals(inputFirstName)) {
            addActionError("First name cannot be empty");
        }
        if ("".equals(inputLastName)) {
            addActionError("Last name cannot be empty");
        }

        if ("".equals(inputPasswordReg)) {
            addActionError("Password cannot be empty.");
        }
        if ("".equals(inputPasswordConf)) {
            addActionError("Password confirmation cannot be empty.");
        }
        if (!inputPasswordConf.equals(inputPasswordReg)) {
            addActionError("Passwords do not match. Please try again.");
        }

    }

    public String getInputUserReg() {
        return inputUserReg;
    }

    public void setInputUserReg(String inputUserReg) {
        this.inputUserReg = inputUserReg;
    }

    public String getInputEmail() {
        return inputEmail;
    }

    public void setInputEmail(String inputEmail) {
        this.inputEmail = inputEmail;
    }

    public String getInputFirstName() {
        return inputFirstName;
    }

    public void setInputFirstName(String inputFirstName) {
        this.inputFirstName = inputFirstName;
    }

    public String getInputLastName() {
        return inputLastName;
    }

    public void setInputLastName(String inputLastName) {
        this.inputLastName = inputLastName;
    }

    public String getInputPasswordReg() {
        return inputPasswordReg;
    }

    public void setInputPasswordReg(String inputPasswordReg) {
        this.inputPasswordReg = inputPasswordReg;
    }

    public String getInputPasswordConf() {
        return inputPasswordConf;
    }

    public void setInputPasswordConf(String inputPasswordConf) {
        this.inputPasswordConf = inputPasswordConf;
    }

    public String getRadio() {
        return radio;
    }

    public void setRadio(String radio) {
        this.radio = radio;
    }

    public String getInputFullName() {
        return inputFullName;
    }

    public void setInputFullName(String inputFullName) {
        this.inputFullName = inputFullName;
    }

    public String getClasses() {
        return classes;
    }

    public void setClasses(String classes) {
        this.classes = classes;
    }
}
