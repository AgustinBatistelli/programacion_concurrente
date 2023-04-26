import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import java.lang.reflect.Type;
import java.io.StringReader;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.FileSystems;
import java.nio.file.FileSystem;

import java.util.*;

public class ProcessTree 
{
  public static void main(String[] args) 
  {
    String self = (args.length == 0) ? "A" : String.valueOf(args[0]);
    
    info(self);
    waitForChildren(spawnChildren(getDataMap(), self));

    try 
    {
      Thread.sleep(5000);
    } catch (InterruptedException e) 
    {
      System.err.println("Se ha producido una interrupción");
    }

  }

  public static void waitForChildren(List<Process> children) 
  {
    for(Process child : children) 
    {
      try 
      {
        child.waitFor();
      } catch (InterruptedException e) 
      {
        System.err.println("Se ha producido una interrupción");
      }
    }
  }

  public static HashMap<String, ArrayList<String>> getDataMap() 
  {
    Gson gson = new Gson();
    Type customType = new TypeToken<HashMap<String, ArrayList<String>>>() {}.getType();
    return gson.fromJson(getFileData(DATA_FILE_NAME), customType); 
  }

  public static String getFileData(String fileName) 
  {
    try 
    {
      return String.join("", 
        Files.readAllLines(FileSystems.getDefault().getPath(fileName))
      );
    } catch (NullPointerException e) 
    {
      e.printStackTrace();
    } catch (IOException e) 
    {
      System.err.println("No se pudo leer el archivo " + fileName);
      e.printStackTrace();
    }
    return "";
  }

  public synchronized static void info(String selfData) 
  {
    try ( PrintWriter out = new PrintWriter(new FileOutputStream(OUT, true), true); ) 
    {
      out.print("Soy el proceso " + selfData + ". ");
      out.print("Mi PID es: " + ProcessHandle.current().pid() + ". ");
      out.print("El PID de mi padre es: " + ProcessHandle.current().parent().get().pid() + ".\n");
      out.flush();
    } catch (IOException e) 
    {
      System.err.println("No se pudo abrir el archivo: " + OUT);
      e.printStackTrace();
    } catch (NoSuchElementException e) 
    {
      System.err.println("No tengo padre: " + OUT);
      e.printStackTrace();
    }
  }

  public static List<Process> spawnChildren(HashMap<String, ArrayList<String>> dataMap, String self) 
  {
    List<Process> children = new ArrayList<>();
    if (dataMap.keySet().contains(self)) 
    {
      for(String childValue : dataMap.get(self)) 
      {
        try 
        {
          children.add(new ProcessBuilder("java", "-cp", ".:gson-2.10.1.jar:gson-2.10.1.jar:", "ProcessTree", childValue, "1>salidaJava", "2>errors").start());
        } catch (IOException e) 
        {
          System.err.println("No se pudieron crear mas procesos:  " + childValue);
        }
      }
    }
    return children;
  }

  final static String DATA_FILE_NAME = "target.json";
  final static String OUT = "miSalidaJava";
}
