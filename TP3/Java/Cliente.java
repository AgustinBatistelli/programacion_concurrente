import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.IOException;

class Cliente
{
    private static final int PORT = 5000;

    public static void main(String[] args) throws IOException
    {
        Socket socketClient = null;
        PrintWriter outputStream = null;
        BufferedReader inputStream = null;

        try
        {
            socketClient = new Socket("127.0.0.1", PORT);
            outputStream = new PrintWriter(socketClient.getOutputStream(), true);;
            inputStream = new BufferedReader(new InputStreamReader(socketClient.getInputStream()));
        }
        catch(IOException e)
        {
            System.err.println("Fail connection to: 127.0.0.1");
            System.exit(1);
        }

       
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Ingrese la cadena de texto para ser analizada:");
        
        String userInput = stdIn.readLine();
        outputStream.println(userInput);
        
        String answertFromServer = inputStream.readLine();
        while( answertFromServer != null && !answertFromServer.isEmpty())
        {
            System.out.println(answertFromServer);
            answertFromServer = inputStream.readLine();
        }


        stdIn.close();
        outputStream.close();
        inputStream.close();
        socketClient.close();
    }
}