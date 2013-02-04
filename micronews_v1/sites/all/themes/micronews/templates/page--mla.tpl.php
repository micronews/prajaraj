<div class="span10 common-list-row">
<div class="row">
 <!-- <div class="total-block span10">
                <div class="row total">

                <?php

                // $mla_id = arg(2);

                // $result = db_query('SELECT COUNT(entity_id) FROM {field_data_field_constituency} WHERE field_constituency_tid  = :field_constituency_tid', array(':field_constituency_tid' => $mla_id ));
                // $result = $result->fetchObject();

                // foreach ($result as $total) {
                // print "<span class='total-title'> Total Micronews Entries: ";
                // print $total;
                // print "</span>";
                // }

                ?>

                </div>

                <div class="row total">
                <?php

                //  $today = strtotime("today");
                //  $tomorrow = strtotime("tomorrow");

                // $result4 = db_query('SELECT  COUNT(micronews_id) FROM {micronews} WHERE (created >= :today  AND created <= :tomorrow AND type  = :type)', array(':today' => $today, ':tomorrow' => $tomorrow, ':type' => 'microupdate'));
                // $result4 = $result4->fetchObject();

                // foreach ($result4 as $total4) {
                // print "<div class='total-data'>" . $total4 . "</div>";
                // }
                // print "<div class='total-title'> Total Micronews Entries today: </div>";

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

<div class="span10 quicktabs-mla">	

<?php

$term = taxonomy_term_load(arg(2));

print "<h4>".$term->name."</h4>";
 
$quicktabs_mla = block_get_blocks_by_region('usable_one');
print render($quicktabs_mla);

?> 

<hr/>
 
 
<div class="">
<span class="btn">
<?php print l("View Visual Analytics", "visual_analytics/".arg(2) ); ?>
</span>
</div>


<h4 class="comment-section-title">Comments</h4>


<?php print views_embed_view('micronews_comments', 'block', arg(2)); ?>
<br> 

<?php ?>
<!-- <a class="facnybox" href="?q=admin/content/micronews/add/microcomments">Add Comment</a>
 -->
<?php // print_r(entity_form('microcomments', 'micronews')); ?>

<button class="fancybox" rel="group" target="_blank" onclick ="popitup('http://localhost/micronews2/?q=admin/content/micronews/add/microcomments')">Add Comment</button>
<br><br><br>

</div>
</div>
</div>
</div>

<script language="javascript" type="text/javascript">
<!--
function popitup(url) {
	newwindow=window.open(url,'name','height=500,width=600');
	if (window.focus) {newwindow.focus()}
	return false;
}

// -->
</script>