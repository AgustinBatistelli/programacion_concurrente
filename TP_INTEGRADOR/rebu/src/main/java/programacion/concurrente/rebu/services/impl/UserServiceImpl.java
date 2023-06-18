package programacion.concurrente.rebu.services.impl;

import programacion.concurrente.rebu.model.User;

import org.springframework.stereotype.Service;

import programacion.concurrente.rebu.model.Cliente;
import programacion.concurrente.rebu.services.UserService;

@Service
public class UserServiceImpl implements UserService {

	private User user;
	
	public UserServiceImpl() {
		this.user = new Cliente("Carlos", "Maidana");
	}
	
	@Override
	public User login(String user, String password) {
		User loggedUser = null;
		if (this.user.getLogin().equals(user) && this.user.getPassword().equals(password)) {
			loggedUser = this.user;
		}
		return loggedUser;
	}

	@Override
	public User signup(String user, String password) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void logout(String user, String password) {
		// TODO Auto-generated method stub
		
	}
	
}