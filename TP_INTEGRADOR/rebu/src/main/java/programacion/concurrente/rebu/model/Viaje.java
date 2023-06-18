package programacion.concurrente.rebu.model;

public class Viaje 
{
	
	private long puntoInicioLat;
	private long puntoInicioLong;
	private long puntoFinalLat;
	private long puntoFinalLong;
	private long precio;
	private double distancia;
	private double duracion;
	private String estado;
	 
	public long getPuntoInicioLat() 
	{
		return puntoInicioLat;
	}
	
	public void setPuntoInicioLat(long puntoInicioLat) 
	{
		this.puntoInicioLat = puntoInicioLat;
	}
	
	public long getPuntoInicioLong() 
	{
		return puntoInicioLong;
	}
	
	public void setPuntoInicioLong(long puntoInicioLong) 
	{
		this.puntoInicioLong = puntoInicioLong;
	}
	
	public long getPuntoFinalLat() 
	{
		return puntoFinalLat;
	}
	
	public void setPuntoFinalLat(long puntoFinalLat) 
	{
		this.puntoFinalLat = puntoFinalLat;
	}
	
	public long getPuntoFinalLong() 
	{
		return puntoFinalLong;
	}
	
	public void setPuntoFinalLong(long puntoFinalLong) 
	{
		this.puntoFinalLong = puntoFinalLong;
	}
	
	public long getPrecio() 
	{
		return precio;
	}
	
	public void setPrecio(long precio) 
	{
		this.precio = precio;
	}
	
	public double getDistancia() 
	{
		return distancia;
	}
	
	public void setDistancia(double distancia) 
	{
		this.distancia = distancia;
	}
	
	public double getDuracion() 
	{
		return duracion;
	}
	
	public void setDuracion(double duracion) 
	{
		this.duracion = duracion;
	}
	
	public String getEstado() 
	{
		return estado;
	}
	
	public void setEstado(String estado) 
	{
		this.estado = estado;
	}
	 
}
