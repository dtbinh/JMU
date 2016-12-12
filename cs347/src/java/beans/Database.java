
package beans;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Database {

    /** JDBC driver name. */
    public static Connection getDatabaseConnection() throws ClassNotFoundException
    {
        Connection connection = null; 
        
        String driver = "com.mysql.jdbc.Driver";
        String url = "jdbc:mysql://us-cdbr-azure-southcentral-e.cloudapp.net/tutors";
        String userId = "b9f979a80b2e16";
        String password = "fa9502d2";
        

        try {
            Class.forName(driver);
            connection = DriverManager.getConnection(url, userId, password);
            
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        return connection;
    }
}