package beans;

import static com.opensymphony.xwork2.Action.INPUT;
import static com.opensymphony.xwork2.Action.SUCCESS;
import com.opensymphony.xwork2.ActionSupport;
import javax.servlet.http.HttpSession;
import static org.apache.commons.lang3.text.WordUtils.capitalizeFully;
import org.apache.struts2.ServletActionContext;

public class UpdateUserAction extends ActionSupport {

    String inputUserReg, inputEmail, inputFirstName, inputLastName, inputFullName, radio, classes;

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

        String username = ServletActionContext.getServletContext().getAttribute("username").toString();
        
        
        rdao.updateData(username, inputFullName, radio, inputEmail, classes);
        
        addActionMessage("Congratulations! Your profile has been updated. Please login with your username and password.");
        return SUCCESS;
    }

    @Override
    public void validate() {
        if ("".equals(inputUserReg)) {
            addActionError("Username cannot be empty.");
        }
        if ("".equals(inputEmail)) {
            addActionError("Email cannot be empty.");
        }
        if ("".equals(inputFirstName)) {
            addActionError("First name cannot be empty");
        }
        if ("".equals(inputLastName)) {
            addActionError("Last name cannot be empty");
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
