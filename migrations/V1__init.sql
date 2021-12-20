create schema if not exists "mnist_d2a23ca6";

create table mnist_d2a23ca6.loss
(
    batch int,
    epoch int,
    loss  float,
    time  timestamp default current_timestamp,
    constraint id primary key (epoch, batch)
);

