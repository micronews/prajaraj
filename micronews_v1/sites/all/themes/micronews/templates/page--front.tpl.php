<div class="span10 common-list-row">
 
  	<div class="row">

	 <div class="total-block span10">
                <div class="span3 total-whole">

                <?php

                $result = db_query('SELECT COUNT(micronews_id) FROM {micronews} WHERE type  = :type', array(':type' => 'microupdate'));
                $result = $result->fetchObject();

               foreach ($result as $total) {
                print "<div class='total-data'>" . $total . "</div>";
                print "<div class='total-title'>Total Updates  </div>";
 
                }

                ?>

                </div>

                <div class="span3 total-today">
                <?php

                 $today = strtotime("today");
                 $tomorrow = strtotime("tomorrow");

                $result4 = db_query('SELECT  COUNT(micronews_id) FROM {micronews} WHERE (created >= :today  AND created <= :tomorrow AND type  = :type)', array(':today' => $today, ':tomorrow' => $tomorrow, ':type' => 'microupdate'));
                $result4 = $result4->fetchObject();

                foreach ($result4 as $total4) {
               
                print "<div class='total-data'>" . $total4 . "</div>";
                print "<div class='total-title'>Updates Today </div>";
                }

                ?>

                </div>


                <div class="span3 total-online">
                <?php
 				$result_users = db_query('SELECT COUNT(uid) FROM {users}');
                $result_users = $result_users->fetchObject();
                foreach ($result_users as $total_users) {
 	            print "<div class='total-data'>" . $total_users . "</div>";
                print "<div class='total-title'>Registered Users </div>";
                }

                ?>

                </div>
        </div>

        </div>


<div class="row">

<?php $constituencies = taxonomy_get_children('constituency'); ?>

<?php //ar_dump($constituency); ?>

<?php foreach ($constituencies as $constituency) { ?>


	<?php $mla_list = taxonomy_get_children($constituency->tid); ?> 

<?php
 
foreach ($mla_list as $mla) { 
	// echo ($i%2);
	
	if($i%2 == 0){
		echo  '<div class="row  dble">';
	}
	
	?>
	<div class='span4 constituency-block'>

	<h4 class='constituency-name'><?php print l($mla->name, 'taxonomy/term/'.$mla->tid); ?></h4>

	<div class="issue issue-water">
	<?php print "<h6 class='issue-title'> Water </h6>" ?>
	<?php print views_embed_view('common', 'block', $mla->tid, 'water'); ?>
	</div>

	<div class="issue issue-electricity">
	<?php print "<h6 class='issue-title'> Electricity </h6>" ?>
	<?php print views_embed_view('common', 'block', $mla->tid, 'electricity'); ?>
	</div>

	<div class="issue issue-law-and-order">
	<?php print "<h6 class='issue-title'> Law and Order </h6>" ?>
	<?php print views_embed_view('common', 'block', $mla->tid, 'lawandorder'); ?>
	</div>

	<div class="issue issue-traffic">
	<?php print "<h6 class='issue-title'> Traffic </h6>" ?>
	<?php print views_embed_view('common', 'block', $mla->tid, 'traffic'); ?>
	</div>

	<div class="issue issue-sewage">
	<?php print "<h6 class='issue-title'> Sewage </h6>" ?>
	<?php print views_embed_view('common', 'block', $mla->tid, 'sewage'); ?>
	</div>
	</div>

<?php


	if($i%2 != 0 and $i!=0){
		echo  '</div>';
	}
	$i++;
 
 }?>

<?php } ?>

<?php

//$visuals = block_get_blocks_by_region('usable_two');
//print render($visuals);

?>



<?php

//$pie = block_get_blocks_by_region('usable_four');
//print render($pie);

?>

</div>

</div>


<?php
		// $result = db_query('SELECT "micronews_id" FROM {micronews} WHERE type  = :type', array(':type' => 'microupdate'));
  //       //$result = $result->fetchObject();


  //       foreach ($result as $r) {
      	
  //      	//$r = $r->fetchObject();
  //       print_r($r->micronews_id);
        
  //       }

  //       print "<br>"; 
  //       print "<br>";
  //       print "<br>";
 

  //       for ($i=0; $i < 28; $i++) { 
        	 
  //       $tomorrow = strtotime("-$i day");
        	  
  //       $j = $i + 1;

  //       $today = strtotime("-$j day");
        	  
  //       $result4 = array();

  //       $result4 = db_query('SELECT  COUNT(micronews_id) FROM {micronews} WHERE (created >= :today  AND created <= :tomorrow AND type  = :type)', array(':today' => $today, ':tomorrow' => $tomorrow, ':type' => 'microupdate'));
  //       $result4 = $result4->fetchObject();

  //           foreach ($result4 as $res4) {
  //               print($res4);
  //               print(" ");
  //           }

       	
 
  //       }

  //       print "<br>"; 
  //       print "<br>";
  //       print "<br>";


        
        // for ($i=0; $i < 28; $i++) { 
             
        //  $tomorrow = strtotime("-$i day");
              
        // $j = $i + 1;

        // $today = strtotime("-$j day");
              
         
        // $result4 = array();
        // $result4 = db_query('SELECT  DISTINCT(created) as created FROM {micronews} WHERE (created >= :today  AND created <= :tomorrow AND type  = :type)', array(':today' => $today, ':tomorrow' => $tomorrow, ':type' => 'microupdate'));
        // //$result4 = db_query('SELECT  DISTINCT(created) as created FROM {micronews} WHERE (created >= :dates  AND type  = :type)', array(':dates' => $dates, ':type' => 'microupdate'));
        // $result4 = $result4->fetchObject();

        // print date('d', $result4->created);
        
        // //$res4 = $res4->fetchObject();
        // //print date('d', $res4->created);

        // }

        //     $dates = array();
        //     $first_day = strtotime('-1 month');
        //     for ($i=0; $i <31 ; $i++) { 
        //         $prec = $i - 30;
        //         $dates[] = date('d-m', strtotime("$prec day"));

        // }

        // var_dump($dates);

        //     foreach ($dates as $date_value) {
        //         print_r($date_value);

        // }
        
 
        
        // //  for ($i=0; $i < 28; $i++) { 
             
        // // $tomorrow = strtotime("tomorrow") - $i * 86400;
              
        // // $j = $i + 1;

        // // $today = strtotime("today") - $i * 86400;
              
        // // $result4 = array();

        // // $result4 = db_query('SELECT  COUNT(micronews_id) FROM {micronews} WHERE (created >= :today  AND created <= :tomorrow AND type  = :type)', array(':today' => $today, ':tomorrow' => $tomorrow, ':type' => 'microupdate'));
        // // $result4 = $result4->fetchObject();

        // //     foreach ($result4 as $res4) {
        // //         print($res4);
        // //         print(" ");
        // //     }

    
        // $mp_id = '5';
        // $mla_list = taxonomy_get_children($mp_id);

        // //dpr($mla_list);


        // // print "<br>"; 
        // // print "<br>";
        // // print "<br>";

        // foreach ($mla_list as $mla_id) {
           
        //    // print $mla_id->tid;

        // $result4 = db_query('SELECT  COUNT(entity_id) FROM {field_data_field_constituency} WHERE (field_constituency_tid = :field_constituency_tid )', array(':field_constituency_tid' => $mla_id->tid));
        // $result4 = $result4->fetchObject();
        // dpr($result4);

            // foreach ($result4 as $res4) {
            //     print($res4);
            //     print(" ");
            // }
         // }

       

        // $mla_tid = '1';
        
        // $issue_type = array('water','electricity','lawandorder','traffic','sewage');
      
        // foreach ($issue_type as $issue) {
          
        // $query = db_select("field_data_field_type", "t");
        // $query->join('field_data_field_constituency', 'c', 't.entity_id = c.entity_id');
        // $query->groupBy('t.entity_id');   
        // $query->fields('t', array('field_type_value'))
        // ->condition('field_type_value', $issue,'=')
        // ->condition('field_constituency_tid', $mla_tid,'=');
        // $result = $query->execute();
        // $count = $result->rowCount();

        // print $count;
        // print "<br>"; 
        //    }
       // $result = $result->fetchObject();
        //var_dump($result);

         // foreach ($result as $res4) {
         //        print_r($res4->field_type_value);
         //        print(" ");
         //    }

        for ($i=0; $i < 31; $i++) { 
           
       //  $tomorrow = strtotime("tomorrow") - $i * 86400;

       //  $today = strtotime("today") - $i * 86400;
       //  $result4 = array();

       //  $result4 = db_query('SELECT  COUNT(micronews_id) FROM {micronews} WHERE (created >= :today  AND created <= :tomorrow AND type = :type) ', array(':today' => $today, ':tomorrow' => $tomorrow, ':type' => 'microupdate'));
       //  $result4 = $result4->fetchObject();

       //  foreach ($result4 as $res4) {
     
       // //print $res4 ;

       //  }
 
        }


        print "<br>"; 
        print "<br>";
        print "<br>";


        for ($i=0; $i < 31; $i++) { 
           
        $tomorrow = strtotime("tomorrow") - $i * 86400;

        $today = strtotime("today") - $i * 86400;

        $mla_tid = '22';
        $query = db_select("micronews", "m");
          $query->join('field_data_field_constituency', 'c', 'm.micronews_id = c.entity_id');
       
          $query->fields('m', array('micronews_id'))
          ->condition('field_constituency_tid', $mla_tid,'=')
             ->condition('created', $tomorrow,'<=')
             ->condition('created', $today,'>=')
             ->condition('type', 'microupdate','=');
          $result = $query->execute();
          $count = $result->rowCount();

          // print_r($count);
          // print " ";
        

        }


            $issue_count = array();
            $mla_tid = '11';
         
        $issue_type = array('water','electricity','lawandorder','traffic','sewage');
        
        $val = 0;
         $total  =array();
        for ($i=0; $i < 10; $i++) { 
           
        $tomorrow = strtotime("tomorrow") - $i * 86400;

        $today = strtotime("today") - $i * 86400;

        foreach ($issue_type as $issue) {
          # code...
        
          
        $query = db_select("field_data_field_type", "t");
        $query->join('field_data_field_constituency', 'c', 't.entity_id = c.entity_id');
        $query->join('micronews', 'm', 't.entity_id = m.micronews_id');
        $query->groupBy('t.entity_id');   
        $query->fields('t', array('entity_id'))
          ->condition('field_type_value', $issue,'=')
          ->condition('field_constituency_tid', $mla_tid,'=')
          ->condition('created', $tomorrow,'<=')
          ->condition('created', $today,'>=');
        $result = $query->execute();
        $count = $result->rowCount();
        

      //  print $count;
       // print " ";
        $total[] = $count;

        }

      

             print "<br>"; 

    $val++;
         
           }

          //var_dump($total);

        print "<br>"; 
        print "<br>";
        print "<br>";
    

    $child_id ='22';
    $mp_id = taxonomy_get_parents($child_id);
   
   // foreach ($mp_id as $value) {
   //   //print ($value->tid);
   // }

    // $issue_count = array();
    // $mla_tid = '11';
    // $mla_tid = '14';
    // $mla_tid = '13' ;
         
    //     $issue_type = array('water','electricity','lawandorder','traffic','sewage');
           
    //     foreach ($issue_type as $issue) {
          
    //     $query = db_select("field_data_field_type", "t");
    //     $query->join('field_data_field_constituency', 'c', 't.entity_id = c.entity_id');
    //     $query->groupBy('t.entity_id');   
    //     $query->fields('t', array('field_type_value'))
    //     ->condition('field_type_value', $issue,'=')
    //     ;
        
        // ->condition(db_or()
        //   ->condition('field_constituency_tid', $mla_tid1,'=')
        //   ->condition('field_constituency_tid', $mla_tid2,'=')
        //   ->condition('field_constituency_tid', $mla_tid3,'=')
        //   );
         
        // $result = $query->execute();
        // $count = $result->rowCount();
    
        //   print_r($count);
         
        //    }


       $parents = taxonomy_get_parents('11');

       foreach ($parents as $parent) {
        $tree = taxonomy_get_tree($parent->vid);
        
        foreach ($tree as $branch) {
          if($branch->depth == 0){
             // print_r($branch);
        }
        
       }

     }

     $tree = taxonomy_get_tree('2');
      foreach ($tree as $branch) {
            if($branch->depth == 0){
         //   print $branch->tid;
          }
              //$branch->tid;
          }


        print "<br>"; 
        print "<br>";
        print "<br>";


       //   var_dump(taxonomy_get_tree('2'));
           
        print "<br>"; 
        print "<br>";
        print "<br>";



?>
