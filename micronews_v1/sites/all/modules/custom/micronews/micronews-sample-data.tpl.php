<?php

/**
 * @file
 * Example tpl file for theming a single micronews-specific theme
 *
 * Available variables:
 * - $status: The variable to theme (while only show if you tick status)
 * 
 * Helper variables:
 * - $micronews: The micronews object this status is derived from
 */
?>

<div class="micronews-status">
  <?php print '<strong>micronews Sample Data:</strong> ' . $micronews_sample_data = ($micronews_sample_data) ? 'Switch On' : 'Switch Off' ?>
</div>