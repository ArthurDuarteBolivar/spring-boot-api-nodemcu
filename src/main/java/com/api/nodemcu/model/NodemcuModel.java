package com.api.nodemcu.model;

import jakarta.persistence.*;
import lombok.Data;

import java.util.Date;
import java.util.TimeZone;

@Entity
@Data
@Table(name="thdados")
public class NodemcuModel {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id")
    private int id;

    @Column(name = "counter")
    private int counter;

    @Column(name = "state")
    private String state;

    @Column(name = "date")
    private Date data;

    @Column(name = "name")
    private String nome;

    @ManyToOne
    @JoinTable(name = "id_user")
    private User id_user;



    @PrePersist
    protected void prePersist() {
        if (this.data == null){
            TimeZone.setDefault(TimeZone.getTimeZone("America/Sao_Paulo"));
            data = new Date();
        }
    }

}

