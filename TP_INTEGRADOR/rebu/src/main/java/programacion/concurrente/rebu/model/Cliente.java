package programacion.concurrente.rebu.model;

public class Cliente extends User
{
	
	private long id;
	private String nombre;
	private String apellido;
	private long telefono;
	
	public Cliente() {
		super();
	}
	
	public Cliente(String user, String password) {
		super(user, password);
	}
	
	public long getId() 
	{
		return id;
	}
	
	public void setId(long id) 
	{
		this.id = id;
	}
	
	public String getNombre() 
	{
		return nombre;
	}
	
	public void setNombre(String nombre) 
	{
		this.nombre = nombre;
	}
	
	public String getApellido() 
	{
		return apellido;
	}
	
	public void setApellido(String apellido) 
	{
		this.apellido = apellido;
	}
	
	public long getTelefono() 
	{
		return telefono;
	}
	
	public void setTelefono(long telefono) 
	{
		this.telefono = telefono;
	}
	
}
