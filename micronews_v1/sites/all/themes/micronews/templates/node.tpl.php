<div class="page-header">
<?php if (!$page){ ?>
				<h1<?php //print $title_attributes; ?>>
				  <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
				</h1>
				
			  <?php } else { ?>
				
				<h1 class="page-title"<?php print $title_attributes; ?>><?php // print $title; ?>
				
				</h1>

				<?php } ?>	
		
</div>

	<?php /*
  // We hide the comments and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);
  hide($content['book_link']);
  //print render($content['body']);
 print render($content);
 print render($content['comments']);
  */
?>


    <div>
	<?php 
	
	hide($content['comments']);
    hide($content['links']);
	print render($content);
	
	
	?>
	<br/>
      
      <div>
       <?php 
	   
	   print render($content['comments']);
	   
	   ?>
      </div>
	  </div>
	  
