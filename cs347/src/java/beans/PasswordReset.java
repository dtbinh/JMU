package beans;

import com.opensymphony.xwork2.ActionSupport;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.math.BigInteger;
import java.net.MalformedURLException;
import java.net.URL;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import java.security.SecureRandom;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import org.apache.struts2.ServletActionContext;

public class PasswordReset extends ActionSupport {

    String inputEmail;
    String password, passwordConf;
    PasswordResetDao prd = new PasswordResetDao();

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getPasswordConf() {
        return passwordConf;
    }

    public void setPasswordConf(String passwordConf) {
        this.passwordConf = passwordConf;
    }

    public String getInputEmail() {
        return inputEmail;
    }

    public void setInputEmail(String inputEmail) {
        this.inputEmail = inputEmail;
    }

    @Override
    public String execute() throws IOException, SQLException, ClassNotFoundException {

        setInputEmail(inputEmail);

        if (prd.checkEmail(inputEmail)) {
            SecureRandom random = new SecureRandom();
            String token = new BigInteger(130, random).toString(32);
            DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
            Calendar nowTim = Calendar.getInstance();
            String timeNow = dateFormat.format(nowTim.getTime());
            System.out.println("The date/time that the token was generated: " + timeNow);
            HttpServletRequest request = ServletActionContext.getRequest();
            URL myURL = new URL("http://"+ request.getServerName()+":" + request.getServerPort() + request.getContextPath() + "/change_password.jsp?token=" + token); //http://localhost:8080/TutorsJMU/change_password.jsp?token=" + token
            prd.setToken(inputEmail, token, timeNow);
            try {
                sendEmail(myURL, prd.getPersonName(), inputEmail);
            } catch (MessagingException ex) {
                Logger.getLogger(PasswordReset.class.getName()).log(Level.SEVERE, null, ex);
            } catch (UnsupportedEncodingException ex) {
                Logger.getLogger(PasswordReset.class.getName()).log(Level.SEVERE, null, ex);
            }
            return SUCCESS;
        } else {
            addActionError("The email was not found.");
        }
        return INPUT;
    }

    public void sendEmail(URL url, String personName, String email) throws MessagingException, UnsupportedEncodingException {
        final String username = "tutors.jmu@gmail.com";
        final String password = "tutors@jmu";

        Properties props = new Properties();
        props.put("mail.smtp.auth", "true");
        props.put("mail.smtp.starttls.enable", "true");
        props.put("mail.smtp.host", "smtp.gmail.com");
        props.put("mail.smtp.port", "587");

        Session session = Session.getInstance(props,
                new javax.mail.Authenticator() {
                    protected PasswordAuthentication getPasswordAuthentication() {
                        return new PasswordAuthentication(username, password);
                    }
                });
        try {
            Message message = new MimeMessage(session);
            message.setFrom(new InternetAddress("tutors.jmu@gmail.com"));
            message.setRecipients(Message.RecipientType.TO,
                    InternetAddress.parse(email));
            message.setSubject("Tutors@JMU Password Reset");
            message.setText("Dear " + personName + ","
                    + "\n\nYou are receiving this email because you have requested to reset your password! "
                    + "\n\n-------------------------------------------------------------------------------- "
                    + "\n How to reset your password: "
                    + "\n1. Click the link below to open the link. "
                    + "\n2. Enter the requested information to reset your password succesfully."
                    + "\n\nReset your password now: "
                    + "\n" + url
                    + "\n\nIf you do not wish to reset your password, you can choose to ignore this email."
                    + "\n\nThank you for choosing us,"
                    + "\nThe Tutors@JMU Team"
                    + "\n\nNotice: The information and attachment(s) contained in this communication are intended for the addressee only,"
                    + " and may be confidential and/or legally privileged. "
                    + "If you have received this communication in error, "
                    + "please contact the sender immediately, and delete this communication from any computer or network system. "
                    + "Any interception, review, printing, copying, re-transmission, dissemination, "
                    + "or other use of, or taking of any action upon this information by persons or entities other than the "
                    + "intended recipient is strictly prohibited by law and may subject them to criminal or civil liability. "
                    + "Tutors@JMU shall not be liable for the improper and/or incomplete transmission of the "
                    + "information contained in this communication or for any delay in its receipt.");
            Transport.send(message);
            System.out.println("Password Request Email Sent");
        } catch (MessagingException e) {
            throw new RuntimeException(e);
        }
    }


    public String getToken() throws ParseException, UnsupportedEncodingException, MalformedURLException, ClassNotFoundException {
        UserDao udao = new UserDao();
        if (!password.equals(passwordConf)) {
            addActionError("The passwords do not match.");
            return "fail";
        } else {

            HttpServletRequest request = ServletActionContext.getRequest();
            String token = (String) request.getSession(false).getAttribute("token");

            DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
            Calendar prev = Calendar.getInstance();
            String timeNow = dateFormat.format(prev.getTime());
            System.out.println("The date that the user requested the page: " + timeNow);

            String requestTime = request.getSession(false).getAttribute("activation-time").toString();
            System.out.println("The token you have received from change_password.jsp is: " + token);
            if (prd.checkToken(token, timeNow, password)) {
                addActionMessage("You have successfully changed your password!");
            } else {
                addActionError("The time for your password reset has expired. Please resubmit your request.");
                return "fail";
            }
            return SUCCESS;
        }
    }
}
