package com.api.nodemcu.modelo;


import org.springframework.data.annotation.CreatedDate;

import javax.persistence.*;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

@Entity
@Table(name="thdados")
public class NodemcuModelo {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "ID")
    private int id;

    @Column(name = "counter")
    private int counter;

    @Column(name = "state", nullable = false, length = 10)
    private String state;

    @Column(name = "data")
    private Date data;

    @PrePersist
    protected void prePersist() {
        if (this.data == null){
            data = new Date();
            System.out.println(data);
        }
    }
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getCounter() {
        return counter;
    }

    public void setCounter(int counter) {
        this.counter = counter;
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public Date getDate() {
        return data;
    } 

    public void setDate(Date data) {
        this.data = data;
    }
//    SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd", locale);
//    java.util.Locale locale = new java.util.Locale("pt","BR");
}
