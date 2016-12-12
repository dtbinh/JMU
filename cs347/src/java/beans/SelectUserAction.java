/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

import com.opensymphony.xwork2.ActionSupport;
import javax.servlet.http.HttpSession;
import org.apache.struts2.ServletActionContext;

/**
 *
 * @author Conner
 */

public class SelectUserAction extends ActionSupport{
    String inputUser;
    String messageTitle;
    String messageBody;
    UserDao ud = new UserDao();

    public String getMessageTitle() {
        return messageTitle;
    }

    public void setMessageTitle(String messageTitle) {
        this.messageTitle = messageTitle;
    }

    public String getMessageBody() {
        return messageBody;
    }

    public void setMessageBody(String messageBody) {
        this.messageBody = messageBody;
    }

    public String getInputUser() {
        return inputUser;
    }

    public void setInputUser(String inputUser) {
        this.inputUser = inputUser;
    }
    
    
    @Override
    public String execute() throws ClassNotFoundException {
        //System.out.println("Inside User Action: " + inputUser);
        HttpSession session = ServletActionContext.getRequest().getSession();
        
        String fromUser = session.getAttribute("username").toString();
        setInputUser(inputUser);
        setMessageTitle(messageTitle);
        setMessageBody(messageBody);
        if (ud.getUsers(inputUser)) 
        {
            ud.insertData(fromUser, inputUser, messageTitle, messageBody);
            return SUCCESS;
        }
        return INPUT;
    }
}