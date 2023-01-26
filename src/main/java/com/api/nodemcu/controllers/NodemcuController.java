package com.api.nodemcu.controllers;


import com.api.nodemcu.modelo.LoginModelo;
import com.api.nodemcu.modelo.NodemcuModelo;
import com.api.nodemcu.repository.LoginRepository;
import com.api.nodemcu.repository.NodemcuRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.util.List;

//@CrossOrigin(origins = "http://localhost:4200")
@RestController
@RequestMapping("/nodemcu"  )
public class NodemcuController {

    @Autowired
    private NodemcuRepository repository;

    @GetMapping()
    @PreAuthorize("hasAnyRole('MANAGERS','USERS')")
    public List<NodemcuModelo> list(){
        return repository.findAll();
    }

    @GetMapping("/{name}")
    @PreAuthorize("hasAnyRole('MANAGERS','USERS')")
    public List<NodemcuModelo> listNome(@PathVariable("name") String name){
        return repository.findByNome(name);
    }

    @PostMapping()
    public NodemcuModelo save(@RequestBody NodemcuModelo nodemcu){
        repository.save(nodemcu);
        return nodemcu;
    }

}
