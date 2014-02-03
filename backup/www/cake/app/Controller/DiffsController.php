<?php
class DiffsController extends AppController {
//    public $helpers = array('Html', 'Form');
    public function index() {
        $this->set('diff', $this->Diff->find('all', array('order' => array('Diff.id' => 'desc'))));
    }
    public function detail() {

    }

    private function test() {
        $time_start = microtime(true);
		//$this->Session->setFlash(__($cmd));
        $output = shell_exec('sudo -H /koppae/queue_dsd.sh >> /tmp/logdsd.txt &');
        $time_end = microtime(true);
        $time = $time_end - $time_start;
        return $time;
    }
    public function view($id = null)
    {
        if(!$id) {
            throw new NotFoundException(__('Invalid view id.'));
        }
        //$cmp = $this->Diff->findById($id, 'id', '');
        $cmp = $this->Diff->findById($id);
        if(!$cmp) {
            throw new NotFoundException(__('Invalid view id.'));
        }
        $this->set('cmp', $cmp);
    }
    
    public function updatestat()
    {
        if($this->request->is('get'))
        {
            $listed = $this->Diff->query("SELECT `diff`.`id`, `diff`.`status` FROM `diff` ORDER BY `diff`.`id` DESC", $cachequeries = false);
            $newlist = array();
            
            foreach($listed as $i) {
                $newlist[$i['diff']['id']] = $i['diff']['status'];
            }
            
            //$this->set('diffs', $listed);
            //$this->set('_serialize', array('diffs'));
            return new CakeResponse(array('body' => json_encode($newlist)));
            //$this->set('_serialize', array('posts'));
    
        }
    }

    public function upload() {
        if($this->request->is('post')) {
            $file = $this->request->data['Diff']['submittedfile'];
            if($file['error'] === UPLOAD_ERR_OK) {
                $id = String::uuid();
                if(move_uploaded_file($file['tmp_name'], '/koppae/working/uploads/'.$id.'.upload')) {
//                  $this->set('temp', $this->Post->create());
                    $this->Diff->create();
                    $this->request->data['Diff']['name'] = $file['name'];
                    $this->request->data['Diff']['filename'] = $id;
                    //$this->request->data['Diff']['samename'] = $id;
                    $this->request->data['Diff']['status'] = 1;
                    $typesin = trim(
                        $this->request->data['Diff']['type'],
                        " \t\n\r\0\x0B"
                    );
                    if($typesin=='') {
                        $typesin = "all";
                    }    
                    $this->request->data['Diff']['type'] = $typesin;
                    
                    if($this->Diff->save($this->request->data)) {
                        $this->request->data['Queue']['diff_id'] = $this->Diff->id;
                        $this->request->data['Queue']['diff_filename'] =
                            $this->request->data['Diff']['filename'];
                        $this->request->data['Queue']['diff_type'] = 
                            $this->request->data['Diff']['type'];
                        if($this->Diff->Queue->save($this->request->data)) {
                            //$this->Session->setFlash(__('Upload Complete.'));
                            $this->test();
                            return $this->redirect(array('action' => 'index'));
                        }
                    }
                    $this->Session->setFlash(__('Cannot add file to database.'));
                    return $this->redirect(array('action' => 'index'));
                }
            }
        }
    }
    
} 
?>
