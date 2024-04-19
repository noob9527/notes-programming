-- database
create database if not exists demo  character set = utf8mb4 collate = utf8mb4_unicode_ci;

drop database demo if exists;

-- table
create table if not exists user
(
    id int not null auto_increment,
    name varchar(255),
    primary key (id)
);

-- index
create index idx_name on user(name);

show index from user;

-- view
create view user_view as select * from user order by id desc;
alter view user_view as select * from user order by id asc;
