select * from user_constraints where 
R_CONSTRAINT_NAME in (select constraint_name from user_constraints where table_name = 'CRM_DEPT') 
