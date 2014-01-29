<?php
echo $this->Html->css('highlight');
print_r($cmp);

$resultpath = $cmp['Diff']['result'];
$samepath = $cmp['Diff']['filesame'];
$srcpath = $cmp['Diff']['filename'];

$src = file($srcpath, FILE_IGNORE_NEW_LINES);
$same = file($samepath, FILE_IGNORE_NEW_LINES);
$result = file($resultpath, FILE_IGNORE_NEW_LINES);
?>
<br /><br /><br />
<div class="row">
    <div class="col-md-4">
        <table class="table table-bordered">
        <tr>
        <td><strong>ID :</strong></td>
        <td><?php echo $cmp['Diff']['id']; ?></td>
        </tr>
        <tr>
        <td><strong>Name :</strong></td>
        <td><?php echo $cmp['Diff']['name']; ?></td>
        </tr>
        <tr>
        <td><strong>Similar File :</strong></td>
        <td><?php echo $cmp['Diff']['filesame']; ?></td>
        </tr>
        <tr>
        <td><strong>Similarity :</strong></td>
        <td><?php echo $cmp['Diff']['percent']; ?>%</td>
        </tr>
        </table>
    </div>
</div>
<div class="row">
    <div class="col-md-6" style="border">
        <table class="table table-bordered">
        <tr><td><?php echo $cmp['Diff']['name']; ?></td></tr>
        <tr>
        <td>
    <?php 
    $m = count($result);
    $n = count($src);
    $start = 0;
    for($i = 0; $i < $m; $i++){
        for($j=$start; $j < $n; $j++) {
            if($src[$j]==$result[$i]) {
                echo "<span class=\"highlightsrc\">";
                echo $src[$j];
                echo "</span>";
                echo "<br \/>";
                break;
            } else {
                echo $src[$j];
                echo "<br \/>";
            }
        }
        $start = $j+=1;
    }
    if($n!=$start) {
        for($i=$start; $i<$n; $i++) {
            echo $src[$i];
            echo "<br \/>";
        }
    }
    ?>
        </td>
        </tr>
        </table>
    </div>
    <div class="col-md-6">
        <table class="table table-bordered">
        <tr><td><?php echo $cmp['Diff']['filesame']; ?></td></tr>
        <tr>
        <td>
    <?php 
    $m = count($result);
    $n = count($same);
    $start = 0;
    for($i = 0; $i < $m; $i++){
        for($j=$start; $j < $n; $j++) {
            if($same[$j]==$result[$i]) {
                echo "<span class=\"highlightsame\">";
                echo $same[$j];
                echo "</span>";
                echo "<br \/>";
                break;
            } else {
                echo $same[$j];
                echo "<br \/>";
            }
        }
        $start = $j+=1;
    }
    if($n!=$start) {
        for($i=$start; $i<$n; $i++) {
            echo $same[$i];
            echo "<br \/>";
        }
    }
    ?>
        </td>
        </tr>
        </table>
    </div>
</div>
