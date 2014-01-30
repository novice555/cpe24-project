<h2>Test Index</h2>
<?php
echo $this->Form->create('Diff', array(
    'enctype' => 'multipart/form-data',
    'controller' => 'diff',
    'action' => 'upload',
    'inputDefaults' => array('class' => 'form-control'),
    'class' => 'form-inline'));

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
            <th>created</th>
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
        <td><?php echo $i['Diff']['created']?></td>
        <td>
            <?php 
            if($i['Diff']['finished'] == true) {
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
            } else {
                echo "N/A";
            }
            
            ?>
        <td>
    </tr>
    <?php endforeach;?>
    <?php unset($i);?>
    </tbody>
</table>
