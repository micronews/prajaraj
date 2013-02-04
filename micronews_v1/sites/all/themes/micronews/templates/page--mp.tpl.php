<div class="span10 common-list-row">

<div class="row">

 <!-- <div class="total-block">
                <div class="span10 total">

                <?php

      //           $mp_id = arg(2);
      //           $mla_id = taxonomy_get_children($mp_id);
      //           //var_dump($mla_id);

      //           foreach ($mla_id as $mla_id_a) {
				  // $result = db_query('SELECT COUNT(entity_id) FROM {field_data_field_constituency} WHERE field_constituency_tid  = :field_constituency_tid', array(':field_constituency_tid' => $mla_id_a->tid));
     	// 		  $result = $result->fetchObject();
      //           	print_r($mla_id_a-);
     	// 		  print_r ($result->entity_id);

         
              //  }

                // $result = db_query('SELECT COUNT(entity_id) FROM {field_data_field_constituency} WHERE field_constituency_tid  = :field_constituency_tid', array(':field_constituency_tid' => array($mla_id) ));
                // $result = $result->fetchObject();

                // foreach ($result as $total) {
                // print "<span class='total-title'> Total Micronews Entries: ";
                // print $total;
                // print "</span>";
                // }

                ?>

                </div>

                <div class="span10 total">
                <?php

                //  $today = strtotime("today");
                //  $tomorrow = strtotime("tomorrow");

                // $result4 = db_query('SELECT  COUNT(micronews_id) FROM {micronews} WHERE (created >= :today  AND created <= :tomorrow AND type  = :type)', array(':today' => $today, ':tomorrow' => $tomorrow, ':type' => 'microupdate'));
                // $result4 = $result4->fetchObject();

                // foreach ($result4 as $total4) {
                // print "<span class='total-title'> Total Micronews Entries today: ";
                // print $total4;
                // print "</span>";
               // }

                ?>

                </div>
        </div> -->

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
<?php $mp_mla_list = taxonomy_get_children(arg(2)); ?> 

<div class="span4">
 
</div>

<div class="span4">
<span class="btn">
<?php print l("View Visual Analytics", "visual_analytics/".arg(2) ); ?>
</span>
</div>

<div class="span4">
 
</div>



<?php $i = 0; ?> 


<?php foreach ($mp_mla_list as $mp_mla) { 

 	

	if($i%2 == 0){
		echo  '<div class="row span10 dble">';
	}


	?>
	
	<div class='span4 constituency-block'>

	<h4 class='constituency-name'><?php print l($mp_mla->name, 'taxonomy/term/'.$mp_mla->tid); ?></h4>

	<div class="issue issue-water">
	<?php print "<h6 class='issue-title'> Water </h6>" ?>
	<?php print views_embed_view('common', 'block', $mp_mla->tid, 'water'); ?>
	</div>

	<div class="issue issue-electricity">
	<?php print "<h6 class='issue-title'> Electricity </h6>" ?>
	<?php print views_embed_view('common', 'block', $mp_mla->tid, 'electricity'); ?>
	</div>

	<div class="issue issue-law-and-order">
	<?php print "<h6 class='issue-title'> Law and Order </h6>" ?>
	<?php print views_embed_view('common', 'block', $mp_mla->tid, 'lawandorder'); ?>
	</div>

	<div class="issue issue-traffic">
	<?php print "<h6 class='issue-title'> Traffic </h6>" ?>
	<?php print views_embed_view('common', 'block', $mp_mla->tid, 'traffic'); ?>
	</div>

	<div class="issue issue-sewage">
	<?php print "<h6 class='issue-title'> Sewage </h6>" ?>
	<?php print views_embed_view('common', 'block', $mp_mla->tid, 'sewage'); ?>
	</div>
	</div>

<?php



	if($i%2 != 0 and $i!=0){
		echo  '</div>';
	}
	$i++;
 }?>

</div>

</div>
</div>