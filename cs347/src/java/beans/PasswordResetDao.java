package beans;

import java.io.UnsupportedEncodingException;
import java.math.BigInteger;
import java.net.MalformedURLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class PasswordResetDao {

    String personName;
    String email;

    public String getPersonName() {
        return personName;
    }

    public void setPersonName(String personName) {
        this.personName = personName;
    }

    public boolean checkEmail(String inputEmail) throws ClassNotFoundException {
        System.out.println("Checking email information...");
        boolean status = false;
        Connection db = null;
        try {
            try {
                Class.forName("com.mysql.jdbc.Driver");
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            db = beans.Database.getDatabaseConnection();
            String query = "select email,name from users where email=?";
            PreparedStatement ps = db.prepareStatement(query);
            ps.setString(1, inputEmail);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                if (rs.getString("email").equals(inputEmail)) {
                    personName = rs.getString("name");
                    email = inputEmail;
                    System.out.println("The persons name from prdao is: " + personName);// I CHANGED THIS!!!
                    status = true; //Email is found.
                } else {
                    status = false; //Email was not found.
                }
            }
        } catch (SQLException e) {
        } finally {
            if (db != null) {
                try {
                    db.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
        return status;
    }

    public void setToken(String email, String token, String time) throws ClassNotFoundException {

        System.out.println("Adding token field to table...");
        String hash = hashPassword(token);
        boolean status = false;
        Connection db = null;
        try {
            try {
                Class.forName("com.mysql.jdbc.Driver");
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            db = beans.Database.getDatabaseConnection();
            String query = "UPDATE tutors.users SET token=?, tokenCreate=? WHERE email=?";
            PreparedStatement ps = db.prepareStatement(query);
            ps.setString(1, token);
            ps.setString(2, time);
            ps.setString(3, email);
            ps.executeUpdate();
        } catch (SQLException e) {
        } finally {
            if (db != null) {
                try {
                    db.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public boolean checkToken(String token, String nowTime, String pass)
            throws ParseException, MalformedURLException, UnsupportedEncodingException, ClassNotFoundException {
        System.out.println("Checking token information...");
        boolean status = false;
        Connection db = null;
        try {
            try {
                Class.forName("com.mysql.jdbc.Driver");
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            db = beans.Database.getDatabaseConnection();
            String query = "select token, tokenCreate from users where token=?";
            PreparedStatement ps = db.prepareStatement(query);
            ps.setString(1, token);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                if (rs.getString("token").equals(token)) {
                    System.out.println("Token was found!");
                    String tokenCreate = rs.getString("tokenCreate");
                    DateFormat df = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
                    Calendar previous = Calendar.getInstance();
                    previous.setTime(df.parse(tokenCreate));
                    Calendar now = Calendar.getInstance();
                    now.setTime(df.parse(nowTime));
                    long diff = now.getTimeInMillis() - previous.getTimeInMillis();
                    if (diff >= 1 * 60 * 15000) {
                        db = beans.Database.getDatabaseConnection();
                        String del_query = "UPDATE users SET token=?, tokenCreate=? WHERE token=?";
                        PreparedStatement nps = db.prepareStatement(del_query);
                        nps.setString(1, null);
                        nps.setString(2, null);
                        nps.setString(3, token);
                        nps.executeUpdate();
                        System.out.println("The Token has expired. Deleting token...");
                    } else {
                        String updatePass = "UPDATE users SET password=? WHERE token=?";
                        PreparedStatement nps2 = db.prepareStatement(updatePass);
                        String hash = hashPassword(pass);
                        nps2.setString(1, hash);
                        nps2.setString(2, token);
                        nps2.executeUpdate();
                        resetToken(token);
                        status = true; // Changed Password.
                    }
                } else {
                    System.out.println("The token was not found!");
                }
            }
        } catch (SQLException e) {
        } finally {
            if (db != null) {
                try {
                    db.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
        return status;
    }

    private static String hashPassword(String password) {
        String digest;
        try {
            MessageDigest md = MessageDigest.getInstance("md5");
            md.reset();
            byte[] bytes = md.digest(password.getBytes());
            digest = new BigInteger(1, bytes).toString(16);
        } catch (NoSuchAlgorithmException nsae) {
            nsae.printStackTrace();
            digest = null;
        }
        return digest;
    }

    private void resetToken(String token) throws MalformedURLException, UnsupportedEncodingException, ClassNotFoundException {
        System.out.println("Resetting Token...");
        boolean status = false;
        Connection db = null;
        try {
            try {
                Class.forName("com.mysql.jdbc.Driver");
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            db = beans.Database.getDatabaseConnection();
            String delQuery = "UPDATE users SET token=?, tokenCreate=? WHERE token=?";
            PreparedStatement ps = db.prepareStatement(delQuery);
            ps.setString(1, null);
            ps.setString(2, null);
            ps.setString(3, token);
            ps.executeUpdate();
        } catch (SQLException e) {
        } finally {
            if (db != null) {
                try {
                    db.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
