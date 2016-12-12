/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;

/**
 *
 * @author Patrick Winters
 */
public class NewPostingDao 
{
    public void submitPost(String name, String type, String subject, String message) throws ClassNotFoundException 
    {
        System.out.println("Submitting New Post...");
        
        Connection db = null; // Connection conn = null;
        try {
            try {
                Class.forName("com.mysql.jdbc.Driver");
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            db = beans.Database.getDatabaseConnection();
            String query = "insert into tutors.postings (name, "
                    + "type, timeCreated, timeRequested, subjects, msg, status) values (?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement ps = db.prepareStatement(query);
            ps.setString(1, name);
            ps.setString(2, type);
            ps.setString(3, "" + System.currentTimeMillis());
            ps.setString(4, "today? I guess");
            ps.setString(5, subject);
            ps.setString(6, message);
            ps.setInt(7, 1);
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
