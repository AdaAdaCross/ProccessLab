<html>
 <head>
  <title>Загрузка внешней программы</title>
 </head>
 <body>
 <?php
   $output=null;
   $retval=null;
   exec('./bee 2', $output, $retval);
   echo "Вернул статус $retval и значение:\n";
   print_r($output);
 ?>
 </body>
</html>
