package com.api.nodemcu.controllers;


import com.api.nodemcu.modelo.NodemcuModelo;
import com.api.nodemcu.repository.NodemcuRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.util.List;

@RestController
@RequestMapping("/nodemcu")
public class NodemcuController {



    @Autowired
    private NodemcuRepository repository;

    @CrossOrigin
    @GetMapping
    public List<NodemcuModelo> list(){
        return repository.findAll();
    }

    @PostMapping
    public void save(@RequestBody NodemcuModelo nodemcu){
        repository.save(nodemcu);
    }

    @Bean
    public WebMvcConfigurer corsConfigurer() {
        return new WebMvcConfigurer() {
            @Override
            public void addCorsMappings(CorsRegistry registry) {
                registry.addMapping("/nodemcu/**").allowedOrigins("http://localhost:8090");
            }
        };
    }


}
