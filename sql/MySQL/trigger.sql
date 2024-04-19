drop table if exists department;
create table department
(
    id int not null auto_increment,
    name varchar(255),
    employee_count int default 0,
    primary key (id)
);

drop table if exists employee;
create table employee
(
    id int not null auto_increment,
    name varchar(255),
    department_id int ,
    primary key (id),
    FOREIGN KEY (department_id) REFERENCES department(id)
);

create trigger employee_insert_trigger after insert on employee 
for each row update department set employee_count = employee_count + 1 
where id = new.department_id;

create trigger employee_delete_trigger after delete on employee 
for each row update department set employee_count = employee_count - 1 
where id = old.department_id;