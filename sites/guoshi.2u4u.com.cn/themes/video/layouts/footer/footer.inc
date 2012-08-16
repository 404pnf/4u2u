<?php 

$plugin = array(                                                                                                                 
          'title' => t('footer'),                                                                                           
          //'icon' => 'test.png',                                                                                                
          'theme' => 'footer',                                                                                               
          'css' => 'footer.css',                                                                                            
          'admin css' => 'footer_admin.css',                                                         
          'panels' => array(                                                                                             
                     'footer_avatar' => t('footer_avatar'),
                     'footer_news' => t('footer_news'),
                     'footer_faq' => t('footer_faq'),
                     ),
);
