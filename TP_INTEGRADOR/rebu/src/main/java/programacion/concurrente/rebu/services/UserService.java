package programacion.concurrente.rebu.services;

import org.springframework.stereotype.Service;

import programacion.concurrente.rebu.model.User;

@Service
public interface UserService {
	public User login(String user, String password);
	public User signup(String user, String password);
	public void logout(String user, String password);
}
