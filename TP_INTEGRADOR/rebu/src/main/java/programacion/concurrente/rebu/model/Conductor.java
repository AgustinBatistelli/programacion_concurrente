package programacion.concurrente.rebu.model;

public class Conductor extends User
{
	private double precioMedio;
	private double posicionActual;
	private String estado;
	private long id;
	private Vehiculo vehículo;
	private String apellido;
	private String nombre;
	private long telefono;
	
	public double getPrecioMedio() {
		return precioMedio;
	}
	public void setPrecioMedio(double precioMedio) {
		this.precioMedio = precioMedio;
	}
	public double getPosicionActual() {
		return posicionActual;
	}
	public void setPosicionActual(double posicionActual) {
		this.posicionActual = posicionActual;
	}
	public String getEstado() {
		return estado;
	}
	public void setEstado(String estado) {
		this.estado = estado;
	}
	public long getId() {
		return id;
	}
	public void setId(long id) {
		this.id = id;
	}
	public Vehiculo getVehículo() {
		return vehículo;
	}
	public void setVehículo(Vehiculo vehículo) {
		this.vehículo = vehículo;
	}
	public String getApellido() {
		return apellido;
	}
	public void setApellido(String apellido) {
		this.apellido = apellido;
	}
	public String getNombre() {
		return nombre;
	}
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}
	public long getTelefono() {
		return telefono;
	}
	public void setTelefono(long telefono) {
		this.telefono = telefono;
	}
	
	

}
