import java.util.Scanner;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Toolkit;
import javax.swing.*;

/**
 * 
 * @author groverf
 */
public class QueryFrame {
	static private String response = null;
	static private JFrame frame;
	
	/**
	 * Prompt the user for input and return a String containing the response.
	 * 
	 * @param prompt The prompt to be displayed to the user
	 */	
	public static String askQuery(String prompt) {
		frame = new JFrame("Query");
		frame.setSize(400,300);
		frame.setLayout(new GridLayout(3,1));
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Toolkit tk = Toolkit.getDefaultToolkit();
		Dimension screenSize = tk.getScreenSize();
		final int WIDTH = screenSize.width;
		final int HEIGHT = screenSize.height;
		// Setup the frame accordingly
		// This is assuming you are extending the JFrame //class
		frame.setSize(WIDTH / 4, HEIGHT / 4);
		frame.setLocation(WIDTH / 4, WIDTH / 4);
		
		JLabel promptField = new JLabel(prompt);
		JPanel promptPanel = new JPanel(new FlowLayout());
		promptPanel.add(promptField);
		frame.add(promptPanel);

		final JTextField inputField = new JTextField(20);
		JPanel textPanel = new JPanel();
		textPanel.add(inputField);
		frame.add(textPanel);
		
		JButton submit = new JButton("Submit");
		submit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				response = inputField.getText();
				frame.dispose();
			}
		});
		
		JPanel submitPanel = new JPanel();
		submitPanel.add(submit);
		frame.add(submitPanel);
		
		frame.setVisible(true);
		
		// Wait for a response before returning
		response = null;
		while (response == null) {
			try  {
    			Thread.sleep(100);
			}
			catch (InterruptedException ie) {}
		}
		
		return response;
	}

}
