delimiter $$
drop function if exists fn_get_name_by_id$$
create function fn_get_name_by_id(_id INT) returns varchar(32) DETERMINISTIC
begin
    declare _name varchar(32) default '';
    select name into _name from user where id = _id;
    return(_name);
end $$
delimiter ;

select fn_get_name_by_id(1);