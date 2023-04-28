import java.net.ServerSocket;
import java.net.Socket;
import java.net.InetAddress;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

class Servidor
{
    private static final int MAX_PEND = 10;
    private static final int PORT = 5000;
    
    public static String processMessage(String message)
    {
        String answer; 
        int characters = 0, numbers = 0, specialCharacters = 0;

        for (int i = 0; i < message.length(); i++)
        {
            char c = message.charAt(i);
            if(Character.isLetter(c))
            {
                characters++;
            } 
            else if (Character.isDigit(c))
            {
                numbers++;
            }
            else
            {
                specialCharacters++;
            }
        }
        
        answer = String.format("Cantidad de caracteres totales: %d\nCantidad de letras: %d", message.length(), characters);
        answer = answer + String.format("\nCantidad de digitos: %d\nCantidad de caracteres que no son letra ni digito: %d",numbers, specialCharacters);       
        return answer;
    }

    public static void main(String[] args) throws IOException
    {
        ServerSocket server = null;
        try
        {
            server = new ServerSocket(PORT, MAX_PEND, InetAddress.getByName("127.0.0.1"));
        }
        catch(IOException e)
        {
            System.err.println("Cloud not listen on port "+PORT);
            System.exit(1);
        }

        System.out.println("Server starts...");
        Socket socketClient = null;
        
        try
        {
            socketClient = server.accept();
        }
        catch(IOException e)
        {
            System.err.println("Accept failed.");
            System.exit(1);
        }
        
        PrintWriter outputStream = new PrintWriter(socketClient.getOutputStream(), true);
        BufferedReader inputStream = new BufferedReader(new InputStreamReader(socketClient.getInputStream()));

        String messageClient = inputStream.readLine();     
        String messageService = processMessage(messageClient);
        outputStream.println(messageService);                                 

        outputStream.close();
        inputStream.close();
        socketClient.close();
        server.close();
    }
}