-- update name by id
delimiter $$
drop procedure if exists sp_update_name_by_id$$
create procedure sp_update_name(in _id INT, IN _name varchar(32))
begin
	update user set name=_name where id = _id;
end $$
delimiter ;

call sp_update_name_by_id(2, 'baz');

-- update all names
delimiter $$
drop procedure if exists sp_update_all_user_name$$
create procedure sp_update_all_user_name(out _rows int, IN _name varchar(32))
begin
    declare total_rows int default 0;
    declare _id int;
    declare cur cursor for select id from user;
    set _rows = 0;
    select count(1) from user into total_rows;
    open cur;
    while _rows < total_rows do
		fetch cur into _id;
        update user set name=_name where id = _id;
        set _rows = _rows + 1;
    end while;
    close cur;
end $$
delimiter ;

-- call
call sp_update_all_user_name(@rows, 'qux');
select @rows;

-- in out inout parameters
delimiter $$
drop procedure if exists sp_test_in_out_params$$
create procedure sp_test_in_out_params(
	in foo int, 
	out bar int, 
	inout baz int
)
begin
	set foo = foo + 1;
    set bar = bar + 1;
    set baz = baz + 1;
end $$
delimiter ;

set @foo = 10, @bar = 10, @baz = 10;
select @foo, @bar, @baz;
call sp_test_in_out_params(@foo, @bar, @baz);
select @foo, @bar, @baz;