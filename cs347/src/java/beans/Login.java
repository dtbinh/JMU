package beans;

import static com.opensymphony.xwork2.Action.INPUT;
import static com.opensymphony.xwork2.Action.SUCCESS;
import com.opensymphony.xwork2.ActionSupport;
import java.io.IOException;
import java.util.Map;
import javax.servlet.http.HttpSession;
import org.apache.struts2.ServletActionContext;
import org.apache.struts2.interceptor.SessionAware;

public class Login extends ActionSupport implements SessionAware{

    private String inputUser, inputPassword;
    boolean previousError = false;
    private Map<String, Object> sessionMap;


    public String getInputUser() {
        return inputUser;
    }

    public void setInputUser(String inputUser) {
        this.inputUser = inputUser;
    }

    public String getInputPassword() {
        return inputPassword;
    }

    public void setInputPassword(String inputPassword) {
        this.inputPassword = inputPassword;
    }

    @Override
    public String execute() throws IOException, ClassNotFoundException {
        UserDao ud = new UserDao(); 
        setInputUser(inputUser);
        setInputPassword(inputPassword);
        if(ud.checkLogin(inputUser, inputPassword)) {
            sessionMap.put("loggedIn", true);
            sessionMap.put("username", inputUser);
            addActionMessage("You have successfully logged in.");
            return SUCCESS;
        }
        else {
            addActionError("Username and/or Password is Incorrect.");
        }       
        return INPUT;
    }
    @Override
    public void validate() {
        if ("".equals(getInputUser())) {
            addActionError("Username cannot be empty");
        }
        if ("".equals(getInputPassword())) {
            addActionError("Password cannot be empty");
        }
    }
    
    
    public String logout() {
        HttpSession session = ServletActionContext.getRequest().getSession();
        session.invalidate();
        return SUCCESS;
    }
    

    @Override
    public void setSession(Map<String, Object> sessionMap) {
        this.sessionMap = sessionMap;
        
    }
} 