/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import beans.Posting;

/**
 *
 * @author Patrick Winters
 */
public class PostingDao 
{
    public ArrayList<Posting> getPostings() throws ClassNotFoundException 
    {
        System.out.println("Getting Postings...");
        boolean status = false;
        Posting messageInfo = new Posting();
        ArrayList<Posting> messages = new ArrayList<Posting>();
        
        Connection db = null; // Connection conn = null;
        try {
            try {
                Class.forName("com.mysql.jdbc.Driver");
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            db = beans.Database.getDatabaseConnection(); 
            String query = "select * from tutors.postings";
            PreparedStatement ps = db.prepareStatement(query);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                System.out.println("HERE");
                messageInfo = new Posting();
                messageInfo.setPostID("" + rs.getInt("postingID"));
                messageInfo.setName(rs.getString("name"));
                messageInfo.setType(rs.getString("type"));
                messageInfo.setTimeCreated(rs.getDate("timeCreated").toString());
                messageInfo.setTimeRequested(rs.getString("timeRequested"));
                messageInfo.setSubjects(rs.getString("subjects"));
                messageInfo.setMsg(rs.getString("msg"));
                messageInfo.setStatus("" + rs.getInt("status"));
                
                messages.add(messageInfo);
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
        return messages;
    }
}
