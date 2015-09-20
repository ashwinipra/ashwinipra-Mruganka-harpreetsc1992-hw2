import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.net.Socket;
import java.io.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.*;
import java.lang.*;


public class ConvClient {
    public static void main(String[] args) {
        //String host = args[0];
        

    	String Host = args[0];			//run as java MsgClient "ipaddress"
    	int portnum = Integer.parseInt(args[1]);
    	String msg1=args[2];			//message
    	String msg2=args[3];
    	String msg3=args[4];
    	
        StringBuilder msg = new StringBuilder();
    
    	String msgf = msg.append(args[2]+ " " + args[3] + " " + args[4]).toString();
      //	String clientname=args[1];		//client name sent to server
        try 
	{
		Socket sock = new Socket(Host,portnum);
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter output = new PrintWriter(sock.getOutputStream(), true);
        BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
              
      //  output.print(clientname);//send client name
		output.flush();
		output.print("\n");//add new line in output
		output.flush();
		System.out.println(msgf);
		output.print(msgf);
	//	output.print(msg2);
	//	output.print(msg3);
		output.flush();
                sock.close();//close socket
                output.close();//close PrintWriter
                in.close();//close BufferedReader
                br.close();

              
	} catch(IOException e) 
		{
              System.out.println("\nError" +e);
          }

    }
}