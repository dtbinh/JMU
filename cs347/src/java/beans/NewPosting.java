package beans;

import javax.servlet.http.HttpSession;
import org.apache.struts2.ServletActionContext;

/**
 *
 * @author jhd29_000
 */
public class NewPosting {
    
    private String subject, comment;
    private NewPostingDao newPostDao;
    
    public String execute() throws ClassNotFoundException
    {
        HttpSession session = ServletActionContext.getRequest().getSession();
        String fromUser = session.getAttribute("username").toString(); 
        
        newPostDao = new NewPostingDao();
        newPostDao.submitPost(fromUser, "student", getSubject(), getComment());
        
        return "success";
    }

    public String getSubject() {
        return subject;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }

    public String getComment() {
        return comment;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }
}
