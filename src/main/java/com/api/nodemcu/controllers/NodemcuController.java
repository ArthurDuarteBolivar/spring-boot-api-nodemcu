package com.api.nodemcu.controllers;


import com.api.nodemcu.modelo.NodemcuModelo;
import com.api.nodemcu.repository.NodemcuRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/nodemcu")
public class NodemcuController {

    @Autowired
    private NodemcuRepository repository;

    @GetMapping
    public List<NodemcuModelo> list(){
        return repository.findAll();
    }

    @PostMapping
    public void save(@RequestBody NodemcuModelo nodemcu){
        repository.save(nodemcu);
    }

}
