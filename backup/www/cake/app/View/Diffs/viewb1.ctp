<?php
echo $this->Html->css('highlight');
//print_r($cmp);

$path = $cmp['Diff']['filename'];
#$resultpath = $cmp['Diff']['result'];
#$samepath = $cmp['Diff']['filesame'];
#$srcpath = $cmp['Diff']['filename'];
$resultpath = '/koppae/working/result/'.$path.'.result';
$samepath = '/koppae/working/same/'.$path.'.same';
$srcpath = '/koppae/working/uploads/'.$path.'.upload';

$src = file($srcpath, FILE_IGNORE_NEW_LINES);
$same = file($samepath, FILE_IGNORE_NEW_LINES);
$result = file($resultpath, FILE_IGNORE_NEW_LINES);
?>
<h1>Result <?php //echo $cmp['Diff']['id']; ?></h1>
<div class="row">
    <div>
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
        <td><?php echo $cmp['Diff']['samename']; ?></td>
        </tr>
        <tr>
        <td><strong>Similarity :</strong></td>
        <td><?php echo $cmp['Diff']['percent']; ?>%</td>
        </tr>
        </table>
    </div>
</div>
<div class="row">
    <div class="col-md-6" style="bordr">
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
                echo htmlspecialchars($src[$j]);
                echo "</span>";
                echo "<br \/>";
                break;
            } else {
                echo htmlspecialchars($src[$j]);
                echo "<br \/>";
            }
        }
        $start = $j+=1;
    }
    if($n!=$start) {
        for($i=$start; $i<$n; $i++) {
            echo htmlspecialchars($src[$i]);
            echo "<br \/>";
        }
    }
    ?>
    <?php 
    /*
    $m = count($result);
    $n = count($src);
    //echo $src[0];
    //echo "<br />";
    //echo $result[0];
    //echo "<br /><br /><br />";
    $start = 0;
    for($i = 0; $i < $m; $i++) {
        for($j=$start; $j < $n; $j++) {
            $a = substr($src[$j], 0, 1000);
            $b = substr($result[$i], 0, 1000);
            //if($src[$j]==$result[$i]) {
            if($a==$b) {
                echo "<span class=\"highlightsrc\">";
                echo strip_tags($src[$j]);
                echo "</span>";
                echo "<br \/>";
                break;
            } else {
                echo strip_tags($src[$j]);
                echo "<br \/>";
            }
        }
        $start = $j+=1;
    }

    if($n!=$start) {
        for($i=$start; $i<$n; $i++) {
            echo strip_tags($src[$i]);
            echo "<br \/>";
        }
    }
*/

    ?>
        </td>
        </tr>
        </table>
    </div>
    <div class="col-md-6">
        <table class="table table-bordered">
        <tr><td><?php echo $cmp['Diff']['samename']; ?></td></tr>
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
                echo htmlspecialchars($same[$j]);
                echo "</span>";
                echo "<br \/>";
                break;
            } else {
                echo htmlspecialchars($same[$j]);
                echo "<br \/>";
            }
        }
        $start = $j+=1;
    }
    if($n!=$start) {
        for($i=$start; $i<$n; $i++) {
            echo htmlspecialchars($same[$i]);
            echo "<br \/>";
        }
    }
    ?>
        </td>
        </tr>
        </table>
    </div>
</div>
