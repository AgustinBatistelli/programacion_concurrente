package programacion.concurrente.rebu.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import programacion.concurrente.rebu.model.User;
import programacion.concurrente.rebu.services.UserService;

@RestController
@RequestMapping("/progra")
public class UserController {

	@Autowired
	UserService userService;
	
//	@GetMapping()
//	public String getLogin() {
//		User user = userService.login("Carlos", "Maidana");
//		return "Se ha logeado " + user.getLogin();
//	}

	@GetMapping("/login")
	public String getLogin() {
		return "login";
	}
	
	
//	@PostMapping("/login")
//	public String login(@RequestParam(name = "user") String userName, @RequestParam(name = "password") String password) {
//		User user = userService.login(userName, password);
//		return (user == null? "El usuario no existe" : "Se ha loggeado " + user.getLogin());
//	}
	
	@PostMapping("/signup")
	public String signup() {
		return "Login";
	}

	@PostMapping("/logout")
	public String logout() {
		return "Logout";
	}
	
}