<?php
echo $this->Html->css('highlight');
//print_r($cmp);

$path = $cmp['Diff']['filename'];
#$resultpath = $cmp['Diff']['result'];
#$samepath = $cmp['Diff']['filesame'];
#$srcpath = $cmp['Diff']['filename'];
$re1path = '/koppae/working/result/'.$path.'.re1';
$re2path = '/koppae/working/result/'.$path.'.re2';
$samepath = '/koppae/working/same/'.$path.'.same';
$srcpath = '/koppae/working/uploads/'.$path.'.upload';

$src = file($srcpath, FILE_IGNORE_NEW_LINES);
$same = file($samepath, FILE_IGNORE_NEW_LINES);
$re1 = file($re1path, FILE_IGNORE_NEW_LINES);
$re2 = file($re2path, FILE_IGNORE_NEW_LINES);
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
    <div>
        <table class="table table-bordered" style="width: 100%; table-layout:fixed;">
        <thead>
        <tr>
            <th><?php echo $cmp['Diff']['name']; ?></th>
            <th><?php echo $cmp['Diff']['samename']; ?></th>
        </tr>
        </thead>
        <tbody>
        <tr>
        <td style="word-wrap: break-word;">
    <?php 
    /*
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
    }*/
    ?>
    <?php 
    
    $m = count($re1);
    $n = count($src);
    //echo $src[0];
    //echo "<br />";
    //echo $result[0];
    //echo "<br /><br /><br />";
    $start = 0;
    $a = '';
    $b = '';
    for($i = 0; $i < $m; $i++) {
        for($j=$start; $j < $n; $j++) {
            //$a = preg_replace(' \t\n\r', '', $src[$j]);
            //$b = preg_replace(' \t\n\r', '', $result[$i]);
            //if($src[$j]==$re1[$i]) {
            //$a = str_replace(array(' ', '\n', '\r'), '', $src[$j]);
            //$b = str_replace(array(' ', '\n', '\r'), '', $result[$i]);
            //$cmp = 0;
            $a = trim($src[$j]);
            $b = trim($re1[$i]);
            //similar_text($a, $b, $cmp);
            //echo htmlspecialchars($b).'<br />';
            if($a==$b) {
            //if($cmp>95) {
                echo "<span class=\"highlightsrc\">";
                echo htmlspecialchars($src[$j]);
                echo "</span>";
                echo "<br />";
                break;
            } else {
                echo htmlspecialchars($src[$j]);
                echo "<br />";
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
        </td>
        <td style="word-wrap: break-word;">
    <?php 
    
    $m = count($re2);
    $n = count($same);
    $start = 0;
    for($i = 0; $i < $m; $i++) {
        for($j=$start; $j < $n; $j++) {
            //$a = substr($same[$j], 0, 1000);
            //$b = substr($result[$i], 0, 1000);
            //if($same[$j]==$re2[$i]) {
            $a = trim($same[$j]);
            $b = trim($re2[$i]);
            if($a==$b) {
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
    <?php /*
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
    */?>
        </td>
        </tr>
        </tbody>
        </table>
    </div>
</div>
