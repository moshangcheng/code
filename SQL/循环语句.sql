declare 
  begin 
  for i in 1 .. 20  loop 
  Insert into CRM_COMPARE (COM_ID,COM_CPT_ID, COM_FIRST_PRICE, COM_SECOND_PRICE,COM_PROJECT_ID) values(SEQUENCE_COMPARE.nextval , 70, sys.dbms_random.value(100, 500)*1000 , sys.dbms_random.value(100, 500)*1000, 362); 
  end loop;
 end;
