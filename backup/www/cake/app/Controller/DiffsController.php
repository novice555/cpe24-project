<?php
class DiffsController extends AppController {
//    public $helpers = array('Html', 'Form');
    public function index() {
        $this->set('diff', $this->Diff->find('all'));
    }

    private function test() {
        $time_start = microtime(true);
        $output = shell_exec('sudo /koppae/queue_dsd.sh');
        $time_end = microtime(true);
        $time = $time_end - $time_start;
        $this->set('error', $output);
        $this->set('exetime', $time);
        
    }
    public function view($id = null)
    {
        if(!$id) {
            throw new NotFoundException(__('Invalid view id.'));
        }
        $cmp = $this->Diff->findById($id);
        if(!$cmp) {
            throw new NotFoundException(__('Invalid view id.'));
        }
        $this->set('cmp', $cmp);
    }
    public function upload() {
        if($this->request->is('post')) {
            $file = $this->request->data['Diff']['submittedfile'];
            if($file['error'] === UPLOAD_ERR_OK) {
                $id = String::uuid();
                if(move_uploaded_file($file['tmp_name'], APP.'uploads'.DS.$id)) {
//                  $this->set('temp', $this->Post->create());
                    $this->Diff->create();
                    $this->request->data['Diff']['name'] = $file['name'];
                    $this->request->data['Diff']['filename'] = APP.'uploads'.DS.$id;
                    $this->request->data['Diff']['filesame'] = "";
                    $this->request->data['Diff']['finished'] = false;
                    $this->request->data['Diff']['result'] = "";

                    if($this->Diff->save($this->request->data)) {
                        $this->Session->setFlash(__('Upload Complete.'));
                        return $this->redirect(array('action' => 'index'));
                    } else {
                        $this->Session->setFlash(__('Cannot add file to database.'));
                    }
                }
            }
        }
    }
    
} 
?>
