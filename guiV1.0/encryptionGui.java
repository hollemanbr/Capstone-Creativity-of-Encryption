import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.BorderLayout;

/*
 * Gui for encryption software.
 * Benjamin Holleman and Richard Winzenried
 */
public class encryptionGui 
{
    private JFrame frame;
    private JTextField key;
    private JTextField plaintext;
    private JLabel output;

    public encryptionGui()
    {
        frame = new JFrame();
        frame.setLocation(100, 100);
        frame.setSize(400, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setTitle("RC4 Encryption");
        initializeComponents();
        frame.pack();
        frame.setVisible(true);
    }

    public void initializeComponents()
    {
        JButton encrypt = new JButton("ENCRYPT");
        encrypt.setName("encrypt");
        JPanel jpButtons = new JPanel();
        jpButtons.add(encrypt);
        frame.add(jpButtons, BorderLayout.PAGE_END);
        output = new JLabel(" ");
        output.setName("output");
        JPanel jpResult = new JPanel();
        jpResult.add(output);
        frame.add(jpResult, BorderLayout.CENTER);
        key = new JTextField(10);
        plaintext = new JTextField(10);
        key.setName("key");
        plaintext.setName("plaintext");
        JPanel jpOp = new JPanel();
        jpOp.add(key);
        jpOp.add(plaintext);
        frame.add(jpOp, BorderLayout.PAGE_START);

        encrypt.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
                encryptClicked();
            }
        });
    }

    public JFrame getFrame()
    {
        return frame;
    }

    public void setFrame(JFrame frame)
    {
        this.frame = frame;
    }

    public JTextField getKey()
    {
        return key;
    }

    public void setKey(JTextField key)
    {
        this.key = key;
    }

    public JTextField getPlaintext()
    {
        return plaintext;
    }

    public void setPlaintext(JTextField plaintext)
    {
        this.plaintext = plaintext;
    }

    public JLabel getOutput() 
    {
        return output;
    }

    public void setOutput(JLabel output)
    {
        this.output = output;
    }

    public void encryptClicked()
    {
        try
        {
            String keyVal = key.getText();
            String plaintextVal = plaintext.getText();
            output.setText("Works");
        }
        catch (NumberFormatException e)
        {
            output.setText("Error");
        }
    }

    public static void main(String[] args)
    {
        encryptionGui gui = new encryptionGui();
    }
}
