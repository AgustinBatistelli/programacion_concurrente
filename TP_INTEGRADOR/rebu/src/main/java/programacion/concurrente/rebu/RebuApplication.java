package programacion.concurrente.rebu;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;

@SpringBootApplication(scanBasePackages = "programacion.concurrente.rebu")
public class RebuApplication extends SpringBootServletInitializer {
	
    @Override
    protected SpringApplicationBuilder configure(SpringApplicationBuilder builder) {
        return builder.sources(RebuApplication.class);
    }

	public static void main(String[] args) {
		SpringApplication.run(RebuApplication.class, args);
	}

}
