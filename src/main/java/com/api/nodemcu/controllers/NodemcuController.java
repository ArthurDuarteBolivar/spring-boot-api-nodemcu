package com.api.nodemcu.controllers;


import com.api.nodemcu.modelo.LoginModelo;
import com.api.nodemcu.modelo.NodemcuModelo;
import com.api.nodemcu.repository.LoginRepository;
import com.api.nodemcu.repository.NodemcuRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.util.List;

@RestController
@CrossOrigin
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
    public NodemcuModelo save(@RequestBody NodemcuModelo nodemcu){
        repository.save(nodemcu);
        return nodemcu;
    }



}
