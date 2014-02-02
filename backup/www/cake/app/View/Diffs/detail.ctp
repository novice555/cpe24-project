<?php
$detail = file('/koppae/data/detail.txt', FILE_IGNORE_NEW_LINES);
$childcount = (count($detail)-7)/2;
//print_r($childcount);
?>
<h2>Data Info</h2>
<table class="table">
<tr><th>Path:</th><td><?php echo $detail[0]; ?></td></tr>
<tr>
<th># of Child:</th><td><?php echo $detail[1]; ?></td>
<th>Static/Duplicate (%):</th><td><?php echo $detail[2].'/'.(100-$detail[2]); ?></td>
</tr>
<tr>
<th>Total file size: </th><td><?php echo $detail[13];?> Bytes</td>
<th>Total file count: </th><td><?php echo $detail[14];?> Files</td>
</tr>
<?php for($i=1; $i<=$childcount; $i++) {?>
<tr>
<th>Child <?php echo $i;?> static file size: </th><td><?php echo $detail[$i*2+1];?> Bytes</td>
<th>Child <?php echo $i;?> file count: </th><td><?php echo $detail[$i*2+2];?> Files</td>
</tr>
<?php } ?>
<tr>
<th>Duplicate file size: </th><td><?php echo $detail[$i*2+1];?> Bytes</td>
<th>Duplicate file count: </th><td><?php echo $detail[$i*2+2];?> Files</td>
</tr>
</table>
