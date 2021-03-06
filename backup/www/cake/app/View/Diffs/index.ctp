<h2>Distributed Computing</h2>
Data Detail
<?php echo $this->Html->link('', array('action' => 'detail'), array('class' => 'glyphicon glyphicon-link')); ?>
<br />
<br />
<h4>Compare File</h4>
<?php
echo $this->Form->create('Diff', array(
    'role' => 'form',
    'enctype' => 'multipart/form-data',
    'controller' => 'diff',
    'action' => 'upload',
    'inputDefaults' => array('class' => 'form-control'),
    'class' => 'form-inline well'));

//echo $this->Form->input('keyword', array('label' => false));
echo $this->Html->div(
    'form-group',
    $this->Form->file('Diff.submittedfile')
);
echo $this->Html->div(
    'form-group',
    $this->Form->input('type', array('label' => false))
);
echo $this->Form->end('Submit');
?>
<table class="table table-hover">
    <thead>
        <tr>
            <th>Id</th>
            <th>Name</th>
            <?php /*
            <th>FileName</th>
            <th>FileSame</th>
            <th>Result</th>
            */ ?>
            <th>Type Search</th>
            <th>created</th>
            <th>Similarity</th>
            <th>Result</th>
        </tr>
    </thead>
    <tbody>
    <?php foreach ($diff as $i): ?>
    <tr>
        <td><?php echo $i['Diff']['id']?></td>
        <td><?php echo $i['Diff']['name']?></td>
        <?php /*
        <td><?php echo $i['Diff']['filename']?></td>
        <td><?php echo $i['Diff']['filesame']?></td>
        <td><?php echo $i['Diff']['result']?></td>
        */ ?>
        <td><?php echo $i['Diff']['type']?></td>
        <td><?php echo $i['Diff']['created']?></td>
        <td>
        <?php 
            if($i['Diff']['percent'] != null)
                echo $i['Diff']['percent'].'%';
            else
                echo 'N/A';
        ?>
        </td>
        <td id="<?php echo $i['Diff']['id']; ?>">
            <?php 
            if($i['Diff']['status'] == 0) {
/*
                echo $this->Form->button('Result', array(
                    'onclick' => 'window.open(\'view/'.$i['Diff']['id'].'\')'
                ));
*/
                echo $this->Html->link(
                    'Result',
                    array('action' => 'view', $i['Diff']['id']),
                    array('class' => 'glyphicon glyphicon-edit', 'target' => '_blank')
                ); 
            } else if($i['Diff']['status'] == 1) {
                echo "In Queue";
            } else if($i['Diff']['status'] == 2) {
                echo "Process";
            } else if($i['Diff']['status'] == 3) {
                echo "Error";
            } else {
                echo "N/A";
            }
            
            ?>
        </td>

    </tr>
    <?php endforeach;?>
    <?php unset($i);?>
    </tbody>
</table>
<?php echo $this->Html->script('check'); ?>

